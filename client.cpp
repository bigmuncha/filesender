#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <array>
#include <vector>
#include <iterator>
#include <algorithm>
using boost::asio::ip::tcp;
int main(int argc, char *argv[]) {

    try{
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
                  <<"...............................\n";

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
        std::cout <<"SEND SUCCESS FINISHED\n";

    }else if(took == 2){
        std::cout << "recv\n";
        char buf[1024];
        std::memset(buf, 0, 1024);
        int len;
        std::ofstream recvfile;
        recvfile.open("recvfile.mp4",std::ios::binary);
        if(!recvfile.is_open()){
            std::cerr <<"Open";
            return 1;
        }
        boost::system::error_code err;

        while (true){

            len = socket.read_some(boost::asio::buffer(buf,1024), err);
            if (len == 0){
                break;
            }
            std::cout <<"recv" << len <<" byte\n";
            //total+=len;
            std::copy(&buf[0],&buf[len],
                      std::ostreambuf_iterator<char>(recvfile));
            std::memset(buf, 0, 1024);

        }


    }
    }catch(std::exception & e){
        std::cerr <<"EXception " << e.what() <<std::endl;
    }
    return 0;
}
