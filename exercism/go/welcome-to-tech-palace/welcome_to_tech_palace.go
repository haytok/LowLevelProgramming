package techpalace

import (
	"strings"
)

// WelcomeMessage returns a welcome message for the customer.
func WelcomeMessage(customer string) string {
	baseString := "Welcome to the Tech Palace, "
	return baseString + strings.ToUpper(customer)
}

// AddBorder adds a border to a welcome message.
func AddBorder(welcomeMsg string, numStarsPerLine int) string {
	starString := strings.Repeat("*", numStarsPerLine)
	return starString + "\n" + welcomeMsg + "\n" + starString
}

// CleanupMessage cleans up an old marketing message.
func CleanupMessage(oldMsg string) string {
	updateOldMsg := strings.Replace(oldMsg, "*", "", -1)
	updateOldMsg = strings.Replace(updateOldMsg, "\n", "", -1)
	updateOldMsg = strings.TrimSpace(updateOldMsg)
	return updateOldMsg
}
