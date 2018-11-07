import scala.io.Source
val filename = "food"
var string = ""

for (line <- Source.fromFile(filename).getLines()) {
  if (line == "%")
  {
      println(string)
      string = ""
  }
  else { string += line + "\n" }
}

/** val line = Source.fromFile(filename).getLines.mkString */
