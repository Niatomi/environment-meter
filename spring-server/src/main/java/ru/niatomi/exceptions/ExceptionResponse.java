package ru.niatomi.exceptions;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.time.LocalDateTime;

/**
 * @author niatomi
 */
@NoArgsConstructor
@Getter
@Setter
public class ExceptionResponse {

    private String message;
    private LocalDateTime dateTime = LocalDateTime.now();

}
