# Qt TCP Client Simulator

Ứng dụng desktop C++/Qt mô phỏng **TCP client** để kết nối đến simulator server qua TCP/IP.

## Tính năng
- Cấu hình host/port và kết nối/ngắt kết nối tới server.
- Gửi payload UTF-8 theo thời gian thực.
- Tùy chọn tự thêm newline vào payload khi gửi.
- Log đầy đủ các sự kiện: connect/disconnect, sent, received, socket error.

## Build nhanh (Qt 6 + CMake)
```bash
cmake -S . -B build
cmake --build build
```

## Cách dùng
1. Chạy simulator server của bạn trước (ví dụ `127.0.0.1:5000`).
2. Chạy app, nhập host/port.
3. Bấm **Connect**.
4. Nhập nội dung tại ô payload và bấm **Send**.
5. Theo dõi dữ liệu gửi/nhận trong **Session Log**.