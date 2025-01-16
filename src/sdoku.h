#ifndef __SDOKU_H__
#define __SDOKU_H__

#include <iostream>
#include <numeric>
#include <vector>

const std::vector<std::vector<int>>& get_sduku_table();

class SdokuTable {
 public:
  const int table_size = 9;            // a sdoku table is 9x9 grid
  const int cell_size = 3;             // each cell is 3x3 grid
  const int sum_in_a_cell = 45;        // 1 + 2 + ... + 8 + 9
  std::vector<std::vector<int>> cell;  // a sdoku table has 9 cells

  explicit SdokuTable(const std::vector<std::vector<int>>& table);
  SdokuTable() = delete;
  ~SdokuTable();

  std::vector<int> get_row_vector(
      int row_index) const;  // get n-th row vector from a sdoku table.
  std::vector<int> get_col_vector(
      int col_index) const;  // get n-th column vector from a sdoku table.
  bool check_vector(
      const std::vector<int>& vector) const;  // check each vector has 1 to 9.
  bool check_table() const;  // check a sdoku table is filled completely.
  void fill_last_value_in_a_cell(int cell_index);
  void fill_last_value_in_a_row(int row_index);
  void fill_last_value_in_a_col(int col_index);
  void show_table() const;
};

void print_vector(const std::vector<int>& vector);

#endif  //__SDOKU_H__
