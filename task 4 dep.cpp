#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const std::string ROOT_DIRECTORY = "./www";

void handle_request(tcp::socket socket) {
    try {
        std::array<char, 1024> buffer;
        std::error_code error;

        // Read the request
        size_t length = socket.read_some(boost::asio::buffer(buffer), error);
        if (error == boost::asio::error::eof) return; // Connection closed cleanly
        else if (error) throw std::system_error(error);

        std::string request(buffer.data(), length);

        // Parse the request (assuming a simple GET request)
        std::istringstream request_stream(request);
        std::string method, path, version;
        request_stream >> method >> path >> version;

        if (method == "GET") {
            // Construct the file path
            std::string file_path = ROOT_DIRECTORY + path;
            if (file_path == ROOT_DIRECTORY + "/") {
                file_path += "index.html"; // Default file
            }

            std::ifstream file(file_path);
            if (file.is_open()) {
                std::stringstream response;
                response << "HTTP/1.1 200 OK\r\n";
                response << "Content-Type: text/html\r\n";
                response << "Content-Length: " << file.tellg() << "\r\n\r\n";
                response << file.rdbuf();
                file.close();

                // Send the response
                boost::asio::write(socket, boost::asio::buffer(response.str()));
            } else {
                // File not found
                std::string not_found_response = "HTTP/1.1 404 Not Found\r\n\r\n";
                boost::asio::write(socket, boost::asio::buffer(not_found_response));
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8080));

        while (true) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            std::thread(handle_request, std::move(socket)).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
