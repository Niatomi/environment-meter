package ru.niatomi.model.domain.schedule;

import lombok.Data;
import org.springframework.data.mongodb.core.mapping.Document;

import javax.persistence.Id;
import java.time.LocalDateTime;

/**
 * @author niatomi
 */
@Document
@Data
public class ExactTime {

    @Id
    private Integer id;

    private LocalDateTime exactTime;

}
