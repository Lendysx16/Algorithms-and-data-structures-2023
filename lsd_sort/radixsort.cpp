#include <iostream>
#include <fstream>


unsigned char **
radix_sort(unsigned char **sequence, size_t sorting_element, size_t string_length, size_t num_of_strings);


int main(int argc, char **argv) {
    std::ifstream input = std::ifstream(argv[1]);
    if (!input) {
        std::cerr << "No input file is found";
        return 1;
    }
    std::ofstream output = std::ofstream(argv[2]);
    if (!output) {
        std::cerr << "No output file is found";
        return 2;
    }
    size_t N;
    size_t M;
    size_t K;
    input >> N >> M >> K;
    unsigned char**buffer = new unsigned char *[M];
    for (size_t i = 0; i < M; ++i) {
        buffer[i] = new unsigned char[N + 1];
        input >> buffer[i];
        buffer[i][N] = '\0';
    }
    unsigned char **new_buffer = new unsigned char*[N];
    for(size_t i = 0; i < N; ++i){
        new_buffer[i] = new unsigned char[M + 1];
        new_buffer[i][M] = '\0';
    }
    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < M; ++j){
            new_buffer[i][j] = buffer[j][i];
        }
        //std::cout << new_buffer[i] << std::endl;
    }
    for (size_t i = 0; i < M; ++i) {
        delete[] buffer[i];
    }
    delete[] buffer;


    for (size_t i = M - 1; i != M - K - 1; --i) {
        unsigned char** sorted_sequence = radix_sort(new_buffer, i, M, N);
        for(size_t j = 0; j < N; ++j){
            new_buffer[j] = sorted_sequence[j];
            sorted_sequence[j] = nullptr;
        }
        delete[] sorted_sequence;
        sorted_sequence = nullptr;
    }

    for(size_t i = 0; i < N; ++i){
        output << new_buffer[i][0];
    }
    for(size_t i = 0; i < N; ++i){
        delete[] new_buffer[i];
    }
    delete[] new_buffer;
    input.close();
    output.close();
    return 0;
}


unsigned char **
radix_sort(unsigned char **sequence, size_t sorting_element, size_t string_length, size_t num_of_strings) {
    unsigned char **result_buffer = new unsigned char *[num_of_strings];


    size_t count_of_chars_arr[256];
    size_t size = num_of_strings;

    for (auto &el: count_of_chars_arr) {
        el = 0;
    }

    unsigned char tmp;
    size_t result_position = 0;


    for (size_t i = 0; i < num_of_strings; ++i) {
        tmp = sequence[i][sorting_element];
        count_of_chars_arr[(unsigned short) tmp] += 1;
    }


    for (size_t i = 255; i != -1; --i) {
        size -= count_of_chars_arr[i];
        count_of_chars_arr[i] = size;
    }


    for (size_t i = 0; i < num_of_strings; ++i) {
        tmp = sequence[i][sorting_element];
        result_position = count_of_chars_arr[(unsigned short) tmp];
        result_buffer[result_position] = sequence[i];
        count_of_chars_arr[(unsigned short) tmp] += 1;
    }

    return result_buffer;

}


