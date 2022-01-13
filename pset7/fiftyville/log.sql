-- Keep a log of any SQL queries you execute as you solve the mystery.

-- See what happened that day.
select * FROM crime_scene_reports WHERE month = 7 AND day = 28;
-- id | year | month | day | street | description
-- 293 | 2020 | 7 | 28 | Axmark Road | Vandalism took place at 12:04. No known witnesses.
-- 294 | 2020 | 7 | 28 | Boyce Avenue | Shoplifting took place at 03:01. Two people witnessed the event.
-- 295 | 2020 | 7 | 28 | Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
-- 296 | 2020 | 7 | 28 | Widenius Street | Money laundering took place at 20:30. No known witnesses.
-- 297 | 2020 | 7 | 28 | Humphrey Lane | Littering took place at 16:36. No known witnesses.

-- Read the interviews contain courthouse.
SELECT transcript FROM interviews WHERE day = 28 AND transcript LIKE "%courthouse%";
-- transcript
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
-- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at the courthouse,
-- I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Get the parking log aroud that time when first interview metioned. (ignored some row)
SELECT * FROM courthouse_security_logs WHERE month = 7 AND day = 28;
-- id | year | month | day | hour | minute | activity | license_plate
-- 260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
-- 261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
-- 262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
-- 263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
-- 264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
-- 265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
-- 266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
-- 267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55

-- Get the atm transaction log around that time when metioned in interview.
SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location ="Fifer Street" AND transaction_type = "withdraw";
-- id | account_number | year | month | day | atm_location | transaction_type | amount
-- 246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
-- 264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
-- 266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
-- 267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
-- 269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
-- 288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
-- 313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
-- 336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35

-- Get the phone call log on 7/28 which less than 1 minute.
SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60;
-- id | caller | receiver | year | month | day | duration
-- 221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
-- 224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
-- 233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
-- 234 | (609) 555-5876 | (389) 555-5198 | 2020 | 7 | 28 | 60
-- 251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
-- 254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
-- 255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
-- 261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
-- 279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
-- 281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54

-- Get the flight log on 7/29 at Fiftyville. (get the flight id)
SELECT * FROM flights INNER JOIN airports WHERE month = 7 AND day = 29 AND airports.city = "Fiftyville" ORDER BY hour LIMIT 1;
-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | id | abbreviation | full_name | city
-- 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 8 | CSF | Fiftyville Regional Airport | Fiftyville

-- Get the airport name both leave and arrive.
-- Hit the answer: escape to London.
SELECT * FROM airports WHERE id = 4 OR id = 8;
-- id | abbreviation | full_name | city
-- 4 | LHR | Heathrow Airport | London
-- 8 | CSF | Fiftyville Regional Airport | Fiftyville

-- Get the name who
-- parked a car at courthouse during that time
-- and had a withdraw at Fiftyville
-- and took a call that day less than 1 minute
-- and took the earliest flight next day.
-- Hit the anwser: who is the thief.
SELECT * FROM people WHERE
license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28)
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location ="Fifer Street" AND transaction_type = "withdraw"))
AND phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
-- id | name | phone_number | passport_number | license_plate
-- 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- Get the name who is the other end at that very two phone call.
-- Hit the anwser: accomplice.
SELECT * FROM people WHERE
phone_number IN (SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE phone_number = "(286) 555-6063" OR phone_number = "(367) 555-5533") AND month = 7 AND day = 28 AND duration <= 60);
-- id | name | phone_number | passport_number | license_plate
-- 250277 | James | (676) 555-6554 | 2438825627 | Q13SVG6
-- 864400 | Berthold | (375) 555-8161 |  | 4V16VO0