package main

import (
    "fmt"
    "math/rand"
    "strings"
    "time"
)

type Visitor struct {
    ticket   string
    duration int
}

func generateTicket() string {
    return fmt.Sprintf("T%d", rand.Intn(1000))
}

func main() {
    rand.Seed(time.Now().UnixNano())

    var numWin int
    fmt.Print("Введите количество окон: ")
    _, err := fmt.Scan(&numWin)
    if err != nil || numWin <= 0 {
        fmt.Println("Некорректное значение окон")
        return
    }

    var visitors []Visitor
    windows := make([][]Visitor, numWin)
    winTimes := make([]int, numWin)

    var cmd string
    fmt.Print("Введите команду: ")
    for {
        _, err := fmt.Scan(&cmd)
        if err != nil {
            break
        }
        cmd = strings.ToUpper(cmd)

        switch cmd {
        case "ENQUEUE":
            var dur int
            fmt.Scan(&dur)
            if dur > 0 {
                ticket := generateTicket()
                visitors = append(visitors, Visitor{ticket, dur})
                fmt.Printf("-> %s\n", ticket)
            } else {
                fmt.Println("Некорректное значение")
            }

        case "DISTRIBUTE":
            for _, v := range visitors {
                minIndex := 0
                for i := 1; i < numWin; i++ {
                    if winTimes[i] < winTimes[minIndex] {
                        minIndex = i
                    }
                }
                windows[minIndex] = append(windows[minIndex], v)
                winTimes[minIndex] += v.duration
            }

            for i := 0; i < numWin; i++ {
                fmt.Printf("Окно %d %d минут: ", i+1, winTimes[i])
                if len(windows[i]) == 0 {
                    fmt.Println("(пусто)")
                } else {
                    var names []string
                    for _, v := range windows[i] {
                        names = append(names, v.ticket)
                    }
                    fmt.Println(strings.Join(names, ", "))
                }
            }
            return

        case "INFO":
            fmt.Println("Доступные команды: ENQUEUE DISTRIBUTE INFO")

        default:
            fmt.Println("Неизвестная команда")
        }
        fmt.Print("Введите команду: ")
    }
}