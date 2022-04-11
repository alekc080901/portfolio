import hashlib


class HashTable(object):

    def __init__(self, length: int):
        self.len = length
        self.table = [[] for _ in range(length)]

    def _find_nearest_empty(self, start: int):
        all_hash = list(range(self.len))
        available_hash = all_hash[start:] + all_hash[:start]

        for cur_hash in available_hash:
            if len(self.table[cur_hash]) == 0:
                return cur_hash

        raise Exception("Таблица переполнена")

    def append(self, key, value):
        hashed_key = hash(str(key)) % self.len

        if len(self.table[hashed_key]) == 0:
            self.table[hashed_key] = [key, value]
        else:
            self.table[self._find_nearest_empty(hashed_key)] = [key, value]

    def get(self, key):
        hashed_key = hash(str(key)) % self.len

        all_hash = list(range(self.len))
        available_hash = all_hash[hashed_key:] + all_hash[:hashed_key]

        for cur_hash in available_hash:
            if len(self.table[cur_hash]) == 0:
                return None

            if self.table[cur_hash][0] == key:
                return self.table[cur_hash][1]
        return None


def main():
    hash_table = HashTable(20)
    source = {"Александр": 21, "Аркадий": 18, "Петруша": 3, "Василек": 11, "Геннадий": 65}
    for item in source.items():
        hash_table.append(item[0], item[1])

    print(hash_table.table)
    print("Информация о Геннадии:", hash_table.get("Геннадий"))


if __name__ == '__main__':
    main()

