#include <uWebSockets/src/App.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>
#include <string_view>
#include <unordered_set>

struct PerSocketData {
    int id;
    std::string usrName;
};

std::unordered_set<uWS::WebSocket<false, true, PerSocketData>*> clients;
int nextId = 1;


int main() {

    using json = nlohmann::json;

    uWS::App()
        .ws<PerSocketData>("/*", {
            .open = [](auto *ws) {
                ws->getUserData()->id = nextId++;
                clients.insert(ws);
                std::cout << "Client " << ws->getUserData()->id << " connected\n";
            },
            .message = [](auto *ws, std::string_view msg, uWS::OpCode) {
                int& id = ws->getUserData()->id;
                // std::cout << "Client " << id << ": " << msg << "\n";
                // ws->send(msg, uWS::OpCode::TEXT);
                
                json obj;
                obj["id"] = id;
                obj["msg"] = msg;

                std::vector<std::uint8_t> bin = json::to_cbor(obj);


                for (auto* client : clients)
                {
                    // if (client != ws)
                    {
                        client->send({reinterpret_cast<char*>(bin.data())}, uWS::OpCode::BINARY);
                    }
                }
            },
            .close = [](auto *ws, int, std::string_view) {
                std::cout << "Client " << ws->getUserData()->id << " disconnected\n";
                clients.erase(ws);
            }
        })
        .listen(9001, [](auto *token) {
            if (token) {
                std::cout << "Listening on ws://localhost:9001\n";
            } else {
                std::cerr << "Failed to listen\n";
            }
        })
        .run();
}
