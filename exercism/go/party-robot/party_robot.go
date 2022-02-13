package partyrobot

import (
	"fmt"
	"strconv"
	"strings"
)

// Welcome greets a person by name.
func Welcome(name string) string {
	return fmt.Sprint("Welcome to my party, ", name, "!")
}

// HappyBirthday wishes happy birthday to the birthday person and exclaims their age.
func HappyBirthday(name string, age int) string {
	return fmt.Sprint(
		"Happy birthday ",
		name,
		"! You are now ",
		strconv.Itoa(age),
		" years old!",
	)
}

// AssignTable assigns a table to each guest.
func AssignTable(name string, table int, neighbor, direction string, distance float64) string {
	s_table := strconv.Itoa(table)
	return fmt.Sprint(
		"Welcome to my party, ",
		name,
		"!\nYou have been assigned to table ",
		strings.Repeat("0", 3 - len(s_table)) + s_table,
		". Your table is ",
		direction,
		", exactly ",
		fmt.Sprintf("%.1f", distance),
		" meters from here.\nYou will be sitting next to ",
		neighbor,
		".",
	)
}
