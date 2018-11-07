import scala.io.Source
import collection.mutable.HashMap

// Print out the cool ascii art!

object HelloWorld {
  def main(args: Array[String]): Unit = {
    val fileName = "alphabet.txt"
    val letters = new HashMap[Int,String]()
    var counter = 1
    var letter = 97

    for (line <- Source.fromFile(fileName).getLines) {
      if (counter == 1) {
        letters.put(letter,line.toString)
      }
      else {
        letters.update(letter, letters.get(letter).get + "\n" + line)
      }
      counter += 1
      if (counter == 5) {
        counter = 1
        letter += 1
      }
    }
    print("Enter a word: ")
    var line = scala.io.StdIn.readLine()
    var i = 0
    for(i <- 0 to line.length() - 1) {
      println(letters.get(line(i)).get)
    }
  }
}
