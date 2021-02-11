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

        char buf[1024];
        std::memset(buf,0,1024);
        int index =0;
        for(auto it = buffer.begin();it != buffer.end();index++,it++){
            if(index>=1024){
                socket.send(boost::asio::buffer(buf));
                index = -1;
                std::memset(buf, 0, 1024);
            } else{
                buf[index] = *it;
            }
        }
        socket.send(boost::asio::buffer(buf));

    }else if(took == 2){
        std::cout << "recv\n";
    }
    return 0;
}
