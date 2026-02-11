#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <atomic>

std::atomic<bool> is_running(true);
std::atomic<bool> is_finished(false);

void timerDisplay(int minutes) {
    int totalSeconds = minutes * 60;
    for (int i = totalSeconds; i >= 0; ) { 
        if (is_running){
            int m = i / 60;
            int s = i % 60;

            std::cout << "\rRemaining Time: "
            << std::setfill('0') << std::setw(2) << m << ":" 
            << std::setfill('0') << std::setw(2) << s 
            << " [Running] (Press Enter to Pause)"<< std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            i--;
        } else {
            //一時停止中の表示
            std::cout << "\rRemaining Time: --:-- [PAUSED]  (Press Enter to Resume)"                  << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    is_finished = true;
    std::cout << "\nTime is up! Take a break." << std::endl;
}

int main() {
    int workTime = 25;
    std::cout << "--- Pomo++ Started (" << workTime << " min) ---" << std::endl;
    std::cout << std::endl;
    std::thread timerThread(timerDisplay, workTime);
    while (!is_finished){
        std::cin.get();//Enterキー待機
        if (is_finished) break;
        is_running = !is_running;
        if (!is_running){
            std::cout << "\033[A\033[K" << std::flush;
        } else {
            std::cout << "\033[A\033[K" << std::flush;
        }
    }
    if (timerThread.joinable()){
        timerThread.join();
    }    
    return 0;
}