trait Array {

    var arr: scala.Array[Int] = Array.empty

    def set_arr(array: scala.Array[Int]): Unit

    def arithmetic_progression(start: Int, n: Int, step: Int): Unit =
        set_arr((start to (n - 1) * step + start by step).toArray)

    def read_from_file(filename: String, n: Int): Unit =
        set_arr(JSONMapper.read_json(filename).slice(0, n))

}
