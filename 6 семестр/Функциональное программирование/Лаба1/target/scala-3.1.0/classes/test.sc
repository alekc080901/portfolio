import scala.annotation.tailrec
import scala.math.{abs, pow}


def ~=(x: Double, y: Double, precision: Double = 0.00000001) = {
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


def form_taylor_table(x0: Double, xk: Double, dx: Double, e: Int) = {
  try {
    assert(x0 < xk && dx > 0 || x0 > xk && dx < 0, "Incorrect interval")
    assert(e >= 0, "Incorrect precision")
    println("x      f(x)         Taylor(x)    TI (Taylor Iterations)")
    for (x <- BigDecimal(x0) until BigDecimal(xk) by BigDecimal(0.1)) {
      assert(!(~=(x.doubleValue, 0.0)), "Zero value in the interval")
      val taylor_res = taylor(x.doubleValue, e)
      println(
        f"${x.doubleValue}%4.2f, " +
          f"${math.sin(x.doubleValue) / x.doubleValue}%10.9f, " +
          f"${taylor_res._1}%10.9f, " +
          f"${taylor_res._2 + 1}"
      )
    }
  } catch {
    case e: AssertionError => println(e.getMessage())
    case e: Exception => println(e)
  }
}
form_taylor_table(-1.2, 0.1, 0.2, 10)

val b = {val a = 1; a}
