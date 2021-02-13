#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <array>
#include <vector>
#include <iterator>
#include <algorithm>
using boost::asio::ip::tcp;
int main(int argc, char *argv[]) {

    boost::asio::io_context io_context;
    tcp::socket socket(io_context);
    tcp::resolver resolver(io_context);
    boost::asio::connect(socket,resolver.resolve("127.0.0.1","9000"));
    std::cout <<"Choose operation: \n"
              <<"1 - send file\n"
              <<"2 - recv file\n";
    int took;
    std::cin>>took;
    if(took == 1){
        std::cout << "you chose send\n"
                  << "input full path of file,\n or file"
                  <<"relatively this folder\n>> ";
        std::string path;
        std::cin >> path;
        std::ifstream file;

        file.open(path,std::ios::binary);
        if(!file.is_open()){
            std::cerr <<"OPEN";
            return 1;
        }
        std::vector<unsigned char>
            buffer(std::istreambuf_iterator<char>(file), {});
        std::cout <<"You chose file " <<path <<'\n'
                  <<"Try send him on your friend\n"
                  <<"...............................";

        int size = buffer.size();
        char buf[1024];
        std::cout <<size <<'\n';
/*
        std::memset(buf,0,1024);
        int index =0;
        for(int i=0,j=0; i < buffer.size() ;j++, i++){
            buf[j] = buffer[i];
            if( j == 1024 ){
                std::cout <<"write\n";
                socket.send(boost::asio::buffer(buf));
                std::memset(buf,0,1024);
                j=-1;
            }
        }
        socket.send(boost::asio::buffer(buf));
*/
        socket.send(boost::asio::buffer(buffer));
    }else if(took == 2){
        std::cout << "recv\n";
    }
    return 0;
}
