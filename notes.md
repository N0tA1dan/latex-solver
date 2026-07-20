# Notes

## 07/08/2026

After some conclusion I decided what the goal of the project is. like wolfram it'll "default" to giving you zeroes, a graph, alternate forms, etc all at once. what this solver would do is just default to either evaluating an expression or finding its zeroes

for example if the input is: 2+3
we would evaluate because theres no unknown variable

but for input: x + 2
we would default to just solving its zeroes.

the rest would be implicit for exmaple if we need the derivative, then the input: d/dx x^2 
would strictly return its derivative, not solving anything or evaluating

## 07/19/2026

the parsing for the differential operator is a bit janky. itll reserve ALL fractions with "d" as the numerator. definitely should fix that
