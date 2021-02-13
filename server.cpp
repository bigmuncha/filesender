#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
    try{
    boost::asio::io_context io_context;
    tcp::socket first_client(io_context);
    tcp::socket second_client(io_context);
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 9000));

    first_client = acceptor.accept();
    second_client = acceptor.accept();

    std::cout <<"accept\n";
    char first_buf[1024];
    std::memset(first_buf,0,1024);
    char second_buf[128];
    std::memset(second_buf,0,128);
    std::cout <<sizeof(first_buf) << '\n';
    std::string res;
    //first_client.read_some(boost::asio::buffer(res));
    //std::ofstream igor;
    //igor.open("recvfile.mp4",std::ios::binary);
    int len;

    int total= 0;
    while(true){
        len = first_client.read_some(boost::asio::buffer(first_buf,1024));
        if (len == 0){
            break;
        }
        std::cout <<"write " << len <<" byte and total =  "
                  << (total= total +len) <<'\n';
        //total+=len;
        second_client.write_some(boost::asio::buffer(first_buf,len));
        std::memset(first_buf, 0, 1024);
        //igor.write(first_buf, sizeof first_buf);
        //std::cout <<"write\n";
    }
    /*std::cout << total << '\n';
        std::copy(&first_buf[0], &first_buf[len],
                  std::ostreambuf_iterator<char>(igor));*/
    }catch(std::exception &e){
        std::cout <<"EXCEPTION" <<e.what() <<std::endl;
    }

        return 0;
}
