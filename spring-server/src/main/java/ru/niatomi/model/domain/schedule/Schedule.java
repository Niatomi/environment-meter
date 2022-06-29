package ru.niatomi.model.domain.schedule;

import lombok.*;

import javax.persistence.*;
import java.time.LocalDateTime;

/**
 * @author niatomi
 */
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class Schedule {

    private Integer id;

    private LocalDateTime checkDateTime;

}
