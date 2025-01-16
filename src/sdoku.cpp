#include "sdoku.h"

const std::vector<std::vector<int> > &get_sduku_table() {
  // clang-format off
    static std::vector<int> cell_0 = {
        0, 3, 5,
        7, 8, 2,
        0, 6, 0};
    static std::vector<int> cell_1 = {
        4, 6, 9,
        1, 0, 5,
        2, 7, 8
      };
    static std::vector<int> cell_2 = {
        2, 7, 8,
        6, 0, 9,
        1, 3, 5};
    static std::vector<int> cell_3 = {
        3, 2, 1,
        8, 0, 4,
        5, 9, 6};
    static std::vector<int> cell_4 = {
        0, 4, 6,
        9, 1, 3,
        8, 2, 0};
    static std::vector<int> cell_5 = {
        8, 9, 7,
        5, 0, 6,
        4, 1, 3};
    static std::vector<int> cell_6 = {
        9, 1, 7,
        6, 0, 3,
        2, 5, 8};
    static std::vector<int> cell_7 = {
        6, 5, 2,
        7, 0, 1,
        3, 9, 4};
    static std::vector<int> cell_8 = {
        0, 8, 0,
        9, 5, 2,
        7, 6, 0};
  // clang-format on

  static const std::vector<std::vector<int> > sdoku_table = {
      cell_0, cell_1, cell_2, cell_3, cell_4, cell_5, cell_6, cell_7, cell_8};

  return sdoku_table;
}

SdokuTable::SdokuTable(const std::vector<std::vector<int> > &table)
    : cell(table) {}

SdokuTable::~SdokuTable() = default;

std::vector<int> SdokuTable::get_row_vector(const int row_index) const {
  // get n-th row vector from a sdoku table.
  std::vector<int> curr_row_vector;

  for (int index_of_cell_in_a_table = 0;
       index_of_cell_in_a_table < this->table_size;
       index_of_cell_in_a_table++) {
    if (index_of_cell_in_a_table / this->cell_size ==
        row_index / this->cell_size) {
      for (int index_of_value_in_a_cell = 0;
           index_of_value_in_a_cell < this->table_size;
           index_of_value_in_a_cell++) {
        if (index_of_value_in_a_cell / this->cell_size ==
            row_index % this->cell_size) {
          curr_row_vector.push_back(
              cell[index_of_cell_in_a_table][index_of_value_in_a_cell]);
        }
      }
    }
  }
  return curr_row_vector;
}

std::vector<int> SdokuTable::get_col_vector(const int col_index) const {
  // get n-th column vector from a sdoku table.
  std::vector<int> curr_column_vector;

  for (int index_of_cell_in_a_table = 0;
       index_of_cell_in_a_table < this->table_size;
       index_of_cell_in_a_table++) {
    if (index_of_cell_in_a_table % this->cell_size ==
        col_index / this->cell_size) {
      for (int index_of_value_in_a_cell = 0;
           index_of_value_in_a_cell < this->table_size;
           index_of_value_in_a_cell++) {
        if (index_of_value_in_a_cell % this->cell_size ==
            col_index % this->cell_size) {
          curr_column_vector.push_back(
              cell[index_of_cell_in_a_table][index_of_value_in_a_cell]);
        }
      }
    }
  }
  return curr_column_vector;
}

bool SdokuTable::check_vector(const std::vector<int> &vector) const {
  // check each vector has 1 to 9.
  for (int i = 0; i < this->table_size; i++) {
    if (std::count(vector.begin(), vector.end(), i) != 1) {
      return false;
    }
  }
  return true;
}

bool SdokuTable::check_table() const {
  // check a sdoku table is filled completely.
  for (int i = 0; i < this->table_size; i++) {
    if (check_vector(this->cell[i])) {
      return false;
    }
  }
  for (int i = 0; i < this->table_size; i++) {
    if (check_vector(get_row_vector(i))) {
      return false;
    }
  }
  for (int i = 0; i < this->table_size; i++) {
    if (check_vector(get_col_vector(i))) {
      return false;
    }
  }
  return true;
}

void SdokuTable::fill_last_value_in_a_cell(const int index_of_cell_in_a_table) {
  if (std::accumulate(this->cell[index_of_cell_in_a_table].begin(),
                      this->cell[index_of_cell_in_a_table].end(),
                      0) == this->desired_sum_value_in_a_cell) {
    // if current cell is completed, return
    return;
  }

  // find the number of zero in a cell.
  if (std::count(this->cell[index_of_cell_in_a_table].begin(),
                 this->cell[index_of_cell_in_a_table].end(), 0) > 1) {
    // if the current cell has two or more empty values, return
    return;
  }

  const int sum =
      std::accumulate(this->cell[index_of_cell_in_a_table].begin(),
                      this->cell[index_of_cell_in_a_table].end(), 0);

  if (sum != desired_sum_value_in_a_cell) {
    // get index of zero in a current vector.
    const auto index_of_zero_value =
        std::find(this->cell[index_of_cell_in_a_table].begin(),
                  this->cell[index_of_cell_in_a_table].end(), 0) -
        this->cell[index_of_cell_in_a_table].begin();
    this->cell[index_of_cell_in_a_table][index_of_zero_value] =
        desired_sum_value_in_a_cell - sum;  // fill last value
  }
}

void SdokuTable::fill_last_value_in_a_row(const int row_index) {
  const std::vector<int> curr_row_vector = get_row_vector(row_index);

  if (std::accumulate(curr_row_vector.begin(), curr_row_vector.end(), 0) ==
      this->desired_sum_value_in_a_cell) {
    // if current row is completed, return
    return;
  }

  // find the number of zero in a current row.
  if (std::count(curr_row_vector.begin(), curr_row_vector.end(), 0) > 1) {
    // if current row has two or more empty values, return
    return;
  }
  const int index_of_zero_value =
      std::find(curr_row_vector.begin(), curr_row_vector.end(), 0) -
      curr_row_vector.begin();
  const int index_of_cell_in_a_table =
      this->cell_size * (row_index / this->cell_size) +
      (index_of_zero_value / this->cell_size);
  const int index_of_value_in_a_cell =
      (row_index % this->cell_size) * this->cell_size +
      (index_of_zero_value % this->cell_size);
  const int sum =
      std::accumulate(curr_row_vector.begin(), curr_row_vector.end(), 0);
  this->cell[index_of_cell_in_a_table][index_of_value_in_a_cell] =
      this->desired_sum_value_in_a_cell - sum;  // fill last value
}

void SdokuTable::fill_last_value_in_a_col(const int col_index) {
  const std::vector<int> curr_column_vector = get_col_vector(col_index);

  if (std::accumulate(curr_column_vector.begin(), curr_column_vector.end(),
                      0) == this->desired_sum_value_in_a_cell) {
    // if current column is completed, return
    return;
  }

  // find the number of zero in a current column.
  if (std::count(curr_column_vector.begin(), curr_column_vector.end(), 0) > 1) {
    // if current column has two or more empty values, return
    return;
  }

  const int index_of_zero_value =
      std::find(curr_column_vector.begin(), curr_column_vector.end(), 0) -
      curr_column_vector.begin();
  const int index_of_cell_in_a_table =
      this->cell_size * (col_index / this->cell_size) +
      (index_of_zero_value / this->cell_size);
  const int index_of_value_in_a_cell =
      (index_of_zero_value % this->cell_size) * this->cell_size +
      (col_index % this->cell_size);
  const int sum =
      std::accumulate(curr_column_vector.begin(), curr_column_vector.end(), 0);
  this->cell[index_of_cell_in_a_table][index_of_value_in_a_cell] =
      this->desired_sum_value_in_a_cell - sum;  // fill last value
}

void SdokuTable::show_table() const {
  for (int i = 0; i < this->table_size; i++) {
    print_vector(this->get_row_vector(i));
  }
  std::cout << std::endl;
}

void print_vector(const std::vector<int> &vector) {
  for (const int i : vector) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}
