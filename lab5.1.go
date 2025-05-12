package main

import (
    "bufio"
    "fmt"
    "os"
    "strconv"
    "strings"
)

var zones = []rune{'A', 'B'}
const (
    nShelves   = 6
    nSections  = 4
    nLevels    = 4
    mCapacity  = 10
)

var warehouse = make(map[string]map[string]int)

func isValid(addr string) (bool, int, int, int) {
    if len(addr) < 4 || len(addr) > 5 {
        return false, 0, 0, 0
    }
    zone := rune(addr[0])
    if zone != 'A' && zone != 'B' {
        return false, 0, 0, 0
    }
    for i := 1; i < len(addr); i++ {
        if addr[i] < '0' || addr[i] > '9' {
            return false, 0, 0, 0
        }
    }

    var shelf, section, level int
    if len(addr) == 4 {
        shelf = int(addr[1] - '0')
        section = int(addr[2] - '0')
        level = int(addr[3] - '0')
    } else {
        shelf = (int(addr[1]-'0') * 10) + int(addr[2]-'0')
        section = int(addr[3] - '0')
        level = int(addr[4] - '0')
    }

    if shelf < 1 || shelf > nShelves || section < 1 || section > nSections || level < 1 || level > nLevels {
        return false, 0, 0, 0
    }
    return true, shelf, section, level
}

func addIt(name string, qty int, addr string) {
    valid, _, _, _ := isValid(addr)
    if !valid {
        fmt.Println("Неверный адрес")
        return
    }

    if warehouse[addr] == nil {
        warehouse[addr] = make(map[string]int)
    }
    current := warehouse[addr][name]
    if current+qty > mCapacity {
        fmt.Println("Превышение вместимости ячейки")
        return
    }
    warehouse[addr][name] += qty
    fmt.Println("Товар добавлен")
}

func removeIt(name string, qty int, addr string) {
    valid, _, _, _ := isValid(addr)
    if !valid {
        fmt.Println("Incorrect addres")
        return
    }
    itemMap, ok := warehouse[addr]
    if !ok || itemMap[name] < qty {
        fmt.Println("Not enough items to remove")
        return
    }

    itemMap[name] -= qty
    if itemMap[name] == 0 {
        delete(itemMap, name)
    }
    if len(itemMap) == 0 {
        delete(warehouse, addr)
    }
    fmt.Println("Товар удалён")
}

func info() {
    cUsed := 0
    capacity := nShelves * nSections * nLevels * 2 * mCapacity
    zoneUsed := make(map[rune]int)

    for addr, items := range warehouse {
        total := 0
        for _, count := range items {
            total += count
        }
        cUsed += total
        zoneUsed[rune(addr[0])] += total
    }

    fmt.Printf("Общая загруженность: %.2f\n", float64(cUsed)*100.0/float64(capacity))
    for _, z := range zones {
        zoneCap := nShelves * nSections * nLevels * mCapacity
        fmt.Printf("Зона %c: %.2f\n", z, float64(zoneUsed[z])*100.0/float64(zoneCap))
    }

    fmt.Println("Содержимое ячеек")
    for addr, items := range warehouse {
        fmt.Print(addr + ": ")
        for name, count := range items {
            fmt.Printf("%s %d ", name, count)
        }
        fmt.Println()
    }

    fmt.Println("Пустые ячейки")
    for _, z := range zones {
        for x := 1; x <= nShelves; x++ {
            for c := 1; c <= nSections; c++ {
                for y := 1; y <= nLevels; y++ {
                    var addr string
                    if x < 10 {
                        addr = fmt.Sprintf("%c%d%d%d", z, x, c, y)
                    } else {
                        addr = fmt.Sprintf("%c%d%d%d", z, x, c, y)
                    }
                    if _, exists := warehouse[addr]; !exists {
                        fmt.Print(addr + " ")
                    }
                }
            }
        }
    }
    fmt.Println()
}

func main() {
    reader := bufio.NewReader(os.Stdin)
    fmt.Println("Введите команду (ADD, REMOVE, INFO) или EXIT для выхода:")
    for {
        fmt.Print("> ")
        line, _ := reader.ReadString('\n')
        line = strings.TrimSpace(line)
        if line == "" {
            continue
        }
        tokens := strings.Fields(line)
        if len(tokens) == 0 {
            continue
        }
        cmd := strings.ToUpper(tokens[0])
        switch cmd {
        case "ADD":
            if len(tokens) < 4 {
                fmt.Println("Недостаточно аргументов")
                continue
            }
            qty, err := strconv.Atoi(tokens[2])
            if err != nil {
                fmt.Println("Некорректное количество")
                continue
            }
            addIt(tokens[1], qty, tokens[3])
        case "REMOVE":
            if len(tokens) < 4 {
                fmt.Println("Недостаточно аргументов")
                continue
            }
            qty, err := strconv.Atoi(tokens[2])
            if err != nil {
                fmt.Println("Некорректное количество")
                continue
            }
            removeIt(tokens[1], qty, tokens[3])
        case "INFO":
            info()
        case "EXIT":
            return
        default:
            fmt.Println("Неизвестная команда")
        }
    }
}
