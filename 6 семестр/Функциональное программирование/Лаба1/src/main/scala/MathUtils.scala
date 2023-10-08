import scala.annotation.tailrec
import scala.math.pow

object MathUtils {
    def ~=(x: Double, y: Double, precision: Double = 0.000000001) = {
        if ((x - y).abs < precision) true else false
    }

    def factorial(n: Int): Double =
        if (n == 0) 1
        else (BigInt(1) to BigInt(n)).product.doubleValue

    @tailrec
    def taylor(x: Double, e: Double, n: Int = 0, acc: Double = 0.0): (Double, Int) = {
        val ser = acc + pow(-1, n) * pow(x, 2 * n) / factorial(2 * n + 1)
        if ((ser - math.sin(x) / x).abs < math.pow(10, -e)) (ser, n) else taylor(x, e, n + 1, ser)
    }
}
