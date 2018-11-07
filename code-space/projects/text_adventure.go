// Code Space Text Adventure. Written in Go.
// No one had previous experience with Go and this what a group came up with in
// an hour trying to make a text adventure game.

package main

import "fmt"
import "bufio"
import ("os")

func main() {
    fmt.Println("You are in your home making smore's, They are yummy, you left")
          fmt.Println("the fire alone and burnt the house down. You are an orphan now.")

    a := "What is your name? "
    fmt.Println(a)

    input := bufio.NewReader (os.Stdin)
    name, _:= input.ReadString('\n')
    fmt.Println("Hello", name[0:len(name) - 1],
      "welcome to the world of orphan pokemon.")
    fmt.Println("Are you a boy or a girl?")
    gender, _:= input.ReadString('\n')

    for gender != "boy\n" && gender != "girl\n" {
      fmt.Println("I asked a question weirdo!!!")
      gender, _= input.ReadString('\n')
  }

  fmt.Println("Ok, so you are a " + gender)
  fmt.Println("Now you have a quest.")
  fmt.Println("You must now find a new home! Would you like to look in the mountains?")

  mountains_yesno, _ := input.ReadString('\n')

  if mountains_yesno == "yes\n" {
     fmt.Println("We're going to the mountains.")
  } else {
     fmt.Println("Would you like to find a cardboard box?")
     cardboard_yesno, _ := input.ReadString('\n')
     if cardboard_yesno == "yes\n" {
       fmt.Println("Alright. Go away then.")
     }
  }
}
