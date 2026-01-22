const messages = document.getElementById("messages");

function show_rcvd(event)
{
    const p = document.createElement("p");
    const data = CBOR.decode(event.data)
    p.textContent = JSON.stringify(data);
    messages.appendChild(p);
}

const ws = new WebSocket("ws://localhost:9001");
ws.binaryType = "arraybuffer";

ws.onmessage = (event) => show_rcvd(event);

function send()
{
    var obj = JSON.parse('{"name":"John", "age":30, "city":"New York"}');
    ws.send(CBOR.encode(obj));
}