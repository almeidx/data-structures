#include "../structures/hashing.c"

char *create_name(char *str) {
  char *name = (char *)malloc(sizeof(char) * (strlen(str) + 1));
  strcpy(name, str);
  return name;
}

void main() {
  HASHING *hashing = create_hashing();

  add_hashing(hashing, create_name("Toni"));
  add_hashing(hashing, create_name("Tome"));
  add_hashing(hashing, create_name("ola"));
  add_hashing(hashing, create_name("Adeus"));
  add_hashing(hashing, create_name("Zeus"));

  show_hashing(hashing);

  save_hash_to_file(hashing, "hashing.dat");

  destroy_hashing(hashing);
}
