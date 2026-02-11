#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

void startTimer(int minutes) {
    int totalSeconds = minutes * 60;

    for (int i = totalSeconds; i >= 0; --i) {
        int m = i / 60;
        int s = i % 60;

        // \r を使って行の先頭に戻り、上書きする
        std::cout << "\r残り時間: " 
        << std::setfill('0') << std::setw(2) << m << ":" 
        << std::setfill('0') << std::setw(2) << s << std::flush;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\n時間になりました。休憩しましょう。" << std::endl;
}

int main() {
    std::cout << "ポモドーロタイマー開始（25分）" << std::endl;
    startTimer(25);
    return 0;
}