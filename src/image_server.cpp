//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

// makes the function read a file names 'filename'
std::vector<uint8_t> get_image(const char* filename)
{
    std::ifstream file(filename, std::ios::binary); // Opens the file, in the raw binary form.

    // Finds the size of the file
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Reads datafrom the file tinto Byte-vector filedata, to be returned.
    std::vector<uint8_t> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
    return fileData;
}

int main()
{
  try
  {
    boost::asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    while (true)
    {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      // loads the image 'cat.jpg'
      auto message = get_image("cat.jpg");

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}