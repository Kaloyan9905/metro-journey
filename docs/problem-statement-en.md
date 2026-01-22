<!--
============================================================================
Copyright (c) 2026 Калоян Ивелинов Milchev (Kaloyan Ivelinov Milchev)
Факултетен номер / Student ID: F118428
Нов български университет (New Bulgarian University)
============================================================================
-->

# Metro Journey

## Description

A city metro system has **N** stations, numbered from **1** to **N**, arranged sequentially along a single line. The train can only move forward - from station **i** to station **j**, where **j > i**.

A passenger needs to travel from station **1** (starting) to station **N** (ending). Some stations are **mandatory to visit** - these are stations whose name contains a specific key string.

Write a program that finds the **minimum number of stations** that must be visited to travel from station 1 to station N, while visiting all mandatory stations.

---

## Input

- **First line:** Integer **T** (1 ≤ T ≤ 50,000) - number of queries

**For each query:**
- **First line:** Integer **N** (1 ≤ N ≤ 100,000) - number of stations
- **Next N lines:** Station names (strings of lowercase Latin letters, length up to 100 characters)
- **Last line:** Key string **K** (length up to 20 characters)

**Constraints:**
- Total number of stations across all queries does not exceed 1,000,000

---

## Output

For each query, output **one line** with the minimum number of stations that must be visited.

---

## Examples

### Input:
```
3
5
centralna
oborishte
serdika
lavov
mladost
ser
6
start
alpha
beta
gamma
delta
end
xyz
7
park
technopark
ecopark
center
parkview
market
finish
park
```

### Output:
```
3
2
5
```

---

## Explanations

**Query 1:** Stations "cen**tra**lna" and "**ser**dika" contain the key string "ser". Station 1 (centralna) is the starting point, station 3 (serdika) is mandatory, station 5 (mladost) is the endpoint. Total: **3 stations**.

**Query 2:** No station contains "xyz". We only visit the starting (1) and ending (6) stations. Total: **2 stations**.

**Query 3:** Stations "park", "technopark", "ecopark", and "parkview" contain "park". The minimum path is: park (1) → technopark (2) → ecopark (3) → parkview (5) → finish (7). Total: **5 stations**.

---

## Notes

- The starting station (1) and ending station (N) are **always** counted, regardless of whether they contain the key string
- If N = 1, the answer is 1
- A mandatory station is any station (between 2 and N-1) whose name contains the key string as a substring

---

## Author

**Kaloyan Ivelinov Milchev**  
Student ID: **F118428**  
New Bulgarian University (NBU)
