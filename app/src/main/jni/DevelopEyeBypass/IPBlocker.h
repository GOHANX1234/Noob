		#ifndef IPBLOCKER_H
#define IPBLOCKER_H

#include <string>
#include <unordered_set>

class IPBlocker {
public:
    // Hàm khởi tạo
    IPBlocker() = default;

    // Hàm hủy
    ~IPBlocker() = default;

    // Hàm để chặn một địa chỉ IP
    void blockIP(const std::string& ip);

    // Hàm để kiểm tra xem một địa chỉ IP có bị chặn hay không
    bool isBlocked(const std::string& ip) const;

private:
    // Tập hợp để lưu trữ các địa chỉ IP bị chặn
    std::unordered_set<std::string> blockedIPs;
};

#endif // IPBLOCKER_H
