package ru.niatomi;

import java.time.LocalDateTime;
import java.time.ZoneOffset;

import static java.time.ZoneOffset.UTC;

/**
 * @author niatomi
 */
public class DemoApplication {

    public static void main(String[] args) {
        LocalDateTime now = LocalDateTime.now();

        Object local;
//        Correct for
        long unixTime2 = now.toEpochSecond(ZoneOffset.of("+04:00"));
        System.out.println(unixTime2);
    }

}
