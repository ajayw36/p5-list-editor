#include "TextBuffer.hpp"

TextBuffer::TextBuffer() : data(CharList()), cursor(data.end()), 
row(1), column(0), index(0) {}

bool TextBuffer::forward() {
    if (cursor == data.end()) {
        return false;
    }
    char current_char = *cursor;
    ++cursor;
    ++index;
    if (current_char == '\n') {
        ++row;
        column = 0;
    }
    else{
        ++column;
    }
    return true;
}

bool TextBuffer::backward() {
    if (cursor == data.begin()) {
        return false;
    }
    --cursor;
    --index;
    if (*cursor == '\n') {
        --row;
        column = compute_column();
    }
    else{
        --column;
    }
    return true;
}

void TextBuffer::insert(char c) {
    data.insert(cursor, c);
    ++index;
    if (c == '\n') {
        ++row;
        column = 0;
    }
    else {
        ++column;
    }
}

bool TextBuffer::remove() {
    if (cursor == data.end()) {
        return false;
    }
    if (*cursor == '\n') {
        column = compute_column();
        --row;
    }
    cursor = data.erase(cursor);
    --index;

    return true;
}

void TextBuffer::move_to_row_start() {
    while(column > 0) {
        backward();
    }
}

void TextBuffer::move_to_row_end() {
    while (cursor != data.end() && *cursor != '\n') {
        forward();
    }
    if (cursor == data.end()) {
        column = compute_column();
    }
}

void TextBuffer::move_to_column(int new_column) {
    if (column == new_column) {
        return;
    }
    move_to_row_start();
    while (column != new_column && cursor != data.end() && *cursor != '\n') {
        forward();
    }
}

bool TextBuffer::up() {
    if (row == 1) {
        return false;
    }    
    int temp = column;
    move_to_row_start();
    backward();
    move_to_column(temp);
    return true;
}

bool TextBuffer::down() {
    int temp = column;
    move_to_row_end();
    if (cursor == data.end()) {
        move_to_column(temp);
        return false;
    }
    else {
        forward();
        move_to_column(temp);
        return true;
    }
}

bool TextBuffer::is_at_end() const {
    return cursor == data.end();
}

char TextBuffer::data_at_cursor() const {
    return *cursor;
}

int TextBuffer::get_row() const {
    return row;
}

int TextBuffer::get_column() const {
    return column;
}

int TextBuffer::get_index() const {
    return index;
}

int TextBuffer::size() const {
    return data.size();
}

std::string TextBuffer::stringify() const {
    return std::string(data.begin(), data.end());
}

int TextBuffer::compute_column() const {
    Iterator it = cursor;
    int col = 0;
    
    while (it != data.begin()) {
        --it;
        if (*it == '\n') {
            return col;
        }
        ++col;
    }
    return col;
}




