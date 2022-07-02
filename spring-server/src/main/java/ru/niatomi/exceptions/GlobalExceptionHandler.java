package ru.niatomi.exceptions;

import com.mongodb.DuplicateKeyException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

/**
 * @author niatomi
 */
@RestControllerAdvice
public class GlobalExceptionHandler {

//    @ExceptionHandler(OpenerAlreadyExistsException.class)
//    @ResponseStatus(HttpStatus.BAD_REQUEST)
//    public ResponseEntity<ExceptionResponse> handleValidExceptions(OpenerAlreadyExistsException ex) {
//        ExceptionResponse exceptionResponse = new ExceptionResponse();
//        exceptionResponse.setStatus(HttpStatus.BAD_REQUEST);
//        exceptionResponse.setDateStamp(LocalDateTime.now());
//        exceptionResponse.setMessage(ex.getMessage());
//        return ResponseEntity.badRequest().body(exceptionResponse);
//    }

    @ExceptionHandler(DuplicateKeyException.class)
    public void handleDuplicateKeyException(DuplicateKeyException ex) {
        System.err.println(ex.getMessage() + "ABOBA");
    }

}
