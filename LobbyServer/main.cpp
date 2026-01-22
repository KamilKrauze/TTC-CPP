#include <uWebSockets/src/App.h>
#include "data_templates/json_templates.hpp"
#include <iostream>
#include <sstream>
#include <string_view>
#include <unordered_set>

struct PerSocketData {
    int id;
};

std::unordered_set<uWS::WebSocket<false, true, PerSocketData>*> clients;
int nextId = 1;

int main() {

    using json = nlohmann::json;

    uWS::App app;

        app.ws<PerSocketData>("/*", {
            .open = [](auto *ws) {
                ws->getUserData()->id = nextId++;
                clients.insert(ws);
                std::cout << "Client " << ws->getUserData()->id << " connected\n";
            },
            .message = [](auto *ws, std::string_view msg, uWS::OpCode op) {
                int& id = ws->getUserData()->id;

                auto logmsg = nlohmann::ordered_json::from_cbor(msg.begin(), msg.end());
                std::cout << logmsg << "\n";
                std::vector<std::uint8_t> bin = nlohmann::ordered_json::to_cbor(tmplts::json::make_character_attribs({0,1,2,3,4,5}));

                for (auto* client : clients)
                {
                    // if (client != ws)
                    {
                        char* bytes = reinterpret_cast<char*>(bin.data());
                        auto binobj = std::string_view(bytes, bin.size());
                        client->send(binobj, uWS::OpCode::BINARY);
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
