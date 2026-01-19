#include "utils.h"

#include <windows.h>
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>

void genid::copy_to_clipboard(const std::string& text) {
    // Abre o clipboard
    if (!OpenClipboard(nullptr)) return;
    EmptyClipboard();

    // Aloca memória global
    HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    if (!hGlob) {
        CloseClipboard();
        return;
    }

    // Copia o texto para a memória
    char* buffer = static_cast<char*>(GlobalLock(hGlob));
    memcpy(buffer, text.c_str(), text.size() + 1);
    GlobalUnlock(hGlob);

    // Define o conteúdo como CF_TEXT
    SetClipboardData(CF_TEXT, hGlob);

    // Fecha o clipboard
    CloseClipboard();
}

std::string genid::make_time_random_id() {
    using namespace std::chrono;
    auto now = time_point_cast<microseconds>(steady_clock::now()).time_since_epoch().count();

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dist;

    uint64_t r = dist(gen);

    std::ostringstream oss;
    oss << std::hex << now << "-" << r;

    return oss.str();
}