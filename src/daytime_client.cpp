//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

     // create a io_context, makes transfer of data possible
    boost::asio::io_context io_context;

    // This set the enpoint, to the inputted ip-adresse 
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime");

    // makes a connection to the endpoint, with the intension to read, or write something.
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    while(true)
    {
      // creates the buffer to write data to
      boost::array<char, 128> buf;
      boost::system::error_code error;

      // Reads data from the server, returns length
      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      // Terminate if no connection 
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      // If there is somthing to write write
      std::cout.write(buf.data(), len);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}