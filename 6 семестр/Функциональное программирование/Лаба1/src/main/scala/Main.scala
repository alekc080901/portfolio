import MathUtils.{taylor, ~=, factorial}

import scala.math.pow

object Main extends App {

    def form_taylor_table(x0: Double, xk: Double, dx: Double, e: Int) = {

            assert(x0 < xk && dx > 0 || x0 > xk && dx < 0, "Incorrect interval!")
            assert(e > 0, "Incorrect precision!")
            println("x      f(x)        Taylor(x)    TI (Taylor Iterations)")
            for (x <- BigDecimal(x0) to BigDecimal(xk) by BigDecimal(0.1)) {
                assert(!(~=(x.doubleValue, 0.0)), "Zero value in the interval")
                val taylor_res = taylor(x.doubleValue, e)
                println(
                    f"${x.doubleValue}%4.2f; " +
                    f"${math.sin(x.doubleValue) / x.doubleValue}%10.9f; " +
                    f"${taylor_res._1}%10.9f; " +
                    f"${taylor_res._2 + 1}"
                )
            }
    }

    try {
        print("Начальный x: ")
        val x0: Double = scala.io.StdIn.readDouble()
        print("Конечный x: ")
        val xk: Double = scala.io.StdIn.readDouble()
        print("Шаг: ")
        val dx: Double = scala.io.StdIn.readDouble()
        print("Количество знаков после запятой: ")
        val e: Int = scala.io.StdIn.readInt()
        form_taylor_table(x0, xk, dx, e)
    } catch {
        case e: AssertionError => println(e.getMessage())
        case e: NumberFormatException => println("Введенное число имеет неверный формат!")
        case e: Exception => println(e)
    }
}
