import java.io.PrintWriter
import play.api.libs.json._

object JSONMapper {

    def write_json(filename: String, array: scala.Array[Int]): PrintWriter = {
        assert(filename.endsWith(".json"))

        val json_string = Json.toJson(array).toString()
        new PrintWriter(filename) { write(json_string); close() }
    }

    def read_json(filename: String): scala.Array[Int] = {
        val source = scala.io.Source.fromFile(filename)
        val lines = try source.mkString finally source.close()
        val json_string = Json.parse(lines)

        json_string.as[scala.Array[Int]]
    }
}
