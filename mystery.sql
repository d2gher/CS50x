-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Frist I took a look at the Crime_scene reports from the time and place of the crime.
SELECT * FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
-- I knew from it that the crime took place at 10:15am and there where some interviews done at Chamberlin Street courthouse with tree witnesses

-- I then went on to check transcriptions from the interviews at that time
SELECT * FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;
-- *CLUE num 1* A witness by the name of Ruth said that after the theft by about 10 minutes the thief got into a car by the courthouse,
-- and the courthouse security cameras might have cought him
-- *CLUE num 2* Another witness named Eugene said she saw the thief on the morning of that day withdrawing money from an ATM on the Fifer Street
-- *CLUE num 3* A man called Raymond said that as the thief was leaving, he/she made a call to some one,
-- they talked for a minute and the thief asked that person to purchase a flight ticket the earlist flight to take him out of Fiftyville tomorrow

-- Following CLUE num 1: I went to check the license plate of the car that left the coursthouse after the theft by about 10 minutes
SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 20 and minute <= 25;
-- And from the security camera logs I have got lincense plates for a few cars
-- Check for who owns those cars
SELECT * FROM people WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 and minute <= 25);
-- id | name | phone_number | passport_number | license_plate
-- 221103 | Patrick | (725) 555-4692 | 2963008352 | 5P2BI95
-- 243696 | Amber | (301) 555-4174 | 7526138472 | 6P58WS2
-- 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
-- 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
-- 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- Following CLUE num 2: I checked the atm transactions to see if the one of the suspects withdrew money that morning
SELECT * FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
-- I then used the account numbers of those who withdrew money that morning to find out their id from the bank accounts data
SELECT name FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));
-- use those IDs to get the names of the suspects
SELECT name FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN( SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));
-- crossing the results with our original suspects from the cars at the courthouse, we find matchs: Elizabeth, Russell, Ernest. the rest is out
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
-- 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE

-- Following CLUE num 3: who is the accomplice?
-- Check the phone calls records at that day
SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;
-- Russell, whos phone number is (770) 555-1861 made a call to someone with the phone number of: (725) 555-3243
-- Ernest, (367) 555-5533 made a call to (375) 555-8161

-- Find out who is our mysterious accomplice
SELECT name, phone_number FROM people WHERE phone_number = "(375) 555-8161" or phone_number = "(725) 555-3243" ;
-- Ernest's : Berthold
-- Russell's: Philips

-- We found out who the theif might be, and his accomplice. but we got two
-- Find the names of the people on the first flight out next day and it's destination
Select name FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour limit 1));
-- Ernest  you son on a *****, I got you, hand me the DUCK!!!
SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour limit 1);
-- London...
