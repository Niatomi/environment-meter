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
        LocalDateTime now1 = LocalDateTime.now().plusWeeks(1L);

        Object local;
//        Correct for
        long unixTime1 = now.toEpochSecond(ZoneOffset.of("+04:00"));
        long unixTime2 = now1.toEpochSecond(ZoneOffset.of("+04:00"));
        System.out.println(unixTime1);
        System.out.println(unixTime2);
        System.out.println(unixTime2 - unixTime1);
    }

}
