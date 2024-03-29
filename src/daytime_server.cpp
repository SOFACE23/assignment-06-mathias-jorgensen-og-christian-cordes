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
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

int main()
{
  try
  {
    // create a io_context, makes transfer of data possible
    boost::asio::io_context io_context;

    // Creates an acceptor, which can accept requests 
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    while (true)
    {
      // Creates a socket which can read an write data.
      // And makes them accept requests
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      // makes the message ready
      std::string message = make_daytime_string();

      // If there is a request to read from the server, the message is written to the buffer, and returned to the client.
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