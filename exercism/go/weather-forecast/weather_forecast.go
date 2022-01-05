// Package weather is to get weather data.
package weather

// CurrentCondition is state.
var CurrentCondition string
// CurrentLocation is location.
var CurrentLocation string

// Forecast is a method.
func Forecast(city, condition string) string {
	CurrentLocation, CurrentCondition = city, condition
	return CurrentLocation + " - current weather condition: " + CurrentCondition
}
