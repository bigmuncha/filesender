#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {

    boost::asio::io_context io_context;
    tcp::socket first_client(io_context);
    tcp::socket second_client(io_context);
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 9000));

    first_client = acceptor.accept();
    second_client = acceptor.accept();

    std::cout <<"accept\n";
    char first_buf[128];
    std::memset(first_buf,0,128);
    char second_buf[128];
    std::memset(second_buf,0,128);

    std::string res;
    first_client.read_some(boost::asio::buffer(res));
    std::ofstream igor;
    igor.open("igor.jpg",std::ios::binary);

    std::copy(res.begin(),res.end(),
              std::ostreambuf_iterator<char>(igor));

    //second_client.write_some(boost::asio::buffer(first_buf));
    return 0;
}
