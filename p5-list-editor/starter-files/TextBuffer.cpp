#include "TextBuffer.hpp"
#include <cassert>

using namespace std;

TextBuffer::TextBuffer()
  : data(), cursor(data.end()), row(1), column(0), index(0) {
}
int TextBuffer::size() const {
  return data.size();
}

bool TextBuffer::is_at_end() const {
  return cursor == data.end();
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

string TextBuffer::stringify() const {
  return string(data.begin(), data.end());
}

char TextBuffer::data_at_cursor() const {
  assert(cursor != data.end());
  return *cursor;
}

void TextBuffer::insert(char c) {
  data.insert(cursor, c);
  ++index;

  if (c == '\n') {
    ++row;
    column = 0;
  } else {
    ++column;
  }
}

bool TextBuffer::forward() {
  if (cursor == data.end()) {
    return false;
  }

  if (*cursor == '\n') {
    ++row;
    column = 0;
  } else {
    ++column;
  }

  ++cursor;
  ++index;

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
  } else {
    --column;
  }

  return true;
}

bool TextBuffer::remove() {
  if (cursor == data.end()) {
    return false;
  }

  cursor = data.erase(cursor);
  return true;
}

int TextBuffer::compute_column() const {
  int col = 0;
  Iterator temp = cursor;

  while (temp != data.begin()) {
    Iterator prev = temp;
    --prev;

    if (*prev == '\n') {
      break;
    }

    ++col;
    temp = prev;
  }

  return col;
}

void TextBuffer::move_to_row_start() {
  while (cursor != data.begin()) {
    Iterator prev = cursor;
    --prev;

    if (*prev == '\n') {
      break;
    }

    backward();
  }
}

void TextBuffer::move_to_row_end() {
  while (cursor != data.end() && *cursor != '\n') {
    forward();
  }
}

void TextBuffer::move_to_column(int new_column) {
  if (new_column < 0) {
    return;
  }

  while (column > new_column) {
    Iterator prev = cursor;
    if (cursor == data.begin()) {
      break;
    }
    --prev;
    if (*prev == '\n') {
      break;
    }
    backward();
  }

  while (column < new_column) {
    if (cursor == data.end() || *cursor == '\n') {
      break;
    }
    forward();
  }
}

bool TextBuffer::up() {
  if (row == 1) {
    return false;
  }

  int target_column = column;

  move_to_row_start();
  backward();
  move_to_row_start();
  move_to_column(target_column);

  return true;
}

bool TextBuffer::down() {
  int target_column = column;

  move_to_row_end();
  if (cursor == data.end()) {
    return false;
  }

  forward();
  move_to_column(target_column);

  return true;
}