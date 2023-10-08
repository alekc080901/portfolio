// Никитин Александр, КИ19-17/1Б, 15 вариант
// Описать трейт для работы с одномерным массивом
// - конструктор, заполняющий заданное в его параметре количество элементов массива арифметической прогрессией, знак числа задается случайным образом;
// - конструктор, заполняющий заданное количество элементов массива из файла с заданным именем
//
// Описать класс расширяющий трейт и реализующий
// - свойство, доступное только для чтения, для получения количества элементов массива, больших 1;
// - метод, вычисляющий произведение модулей элементов, расположенных до (левее) последнего отрицательного элемента.
// .

object Roga {
    var a = 1
    println("123")
}


object Main extends App {

    def assess_array(array: ArrayImpl): Unit = {
        try {
            ArrayImpl.print_all(array)
        } catch {
            case e: AssertionError => println(e.getMessage)
            case e: Exception => println(e)
        }
    }

    val arr = ArrayImpl()
    assess_array(arr)
    println()

    arr.arithmetic_progression(-6, 6, 2)
    assess_array(arr)
    println()

    arr.read_from_file("filename.json", 4)
    assess_array(arr)
}
