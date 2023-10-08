import scala.math.abs

case class ArrayImpl() extends Array {
    var greater_one_amount: Int = 0

    def product_last_negative: Int = {
        assert(!arr.isEmpty && arr.findLast(_ < 0).nonEmpty)

        arr.slice(0, arr.lastIndexOf(arr.findLast(_ < 0).get)).map(abs).product
    }

    def set_arr(array: scala.Array[Int]): Unit = {
        arr = array
        greater_one_amount = arr.count(_ > 1)
    }
}

object ArrayImpl {
    def print_array(array: ArrayImpl): Unit =
        println("Array: " + array.arr.mkString("Array(", ", ", ")"))

    def print_amount(array: ArrayImpl): Unit =
        println("Amount of elements greater than 1: " + array.greater_one_amount)

    def print_product(array: ArrayImpl): Unit =
        println("Product of elements left of last negative: " + array.product_last_negative)

    def print_all(array: ArrayImpl): Unit = {
        print_array(array)
        print_amount(array)
        print_product(array)
    }
}
