#include "sdoku.h"

int main() {
  SdokuTable table(get_sduku_table());
  std::cout << "Start" << std::endl;
  table.show_table();

  while (!table.check_table()) {
    for (int i = 0; i < table.table_size; i++) {
      table.fill_last_value_in_a_col(i);
    }
    for (int i = 0; i < table.table_size; i++) {
      table.fill_last_value_in_a_row(i);
    }
    for (int i = 0; i < table.table_size; i++) {
      table.fill_last_value_in_a_cell(i);
    }
  }
  std::cout << "Completed" << std::endl;
  table.show_table();

  return 0;
}
