package ru.niatomi.model.domain.schedule;

import lombok.AllArgsConstructor;
import lombok.Data;
import org.springframework.data.mongodb.core.mapping.Document;

import javax.persistence.Id;
import javax.validation.constraints.Future;
import java.time.LocalDateTime;

/**
 * @author niatomi
 */
@Document
@Data
@AllArgsConstructor
public class ExactTime {

    @Id
    private Long id;

    @Future
    private LocalDateTime exactTime;

}
