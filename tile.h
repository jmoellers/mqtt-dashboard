# if !defined(TILE_H) /* { */
# define	TILE_H

# include	<mosquitto.h>
# include	<mosquittopp.h>
# include	<QtWidgets>
# include	"SquareFrame.h"

// class tile : public mosqpp::mosquittopp, public QFrame
class tile : public SquareFrame, public mosqpp::mosquittopp
{
    // Q_OBJECT
public:
    tile(QString _title, QString _topic, QString _unit, QSettings *settings);
    ~tile();
private:
    QVBoxLayout *layout;
    QLabel *title_label;
    QLabel *value_label;
    QString unit, topic;
    QMap<QString,QString>options;
    QString host, user, pass;
    uint port;
    void on_connect(int rc);
    void on_message(const struct mosquitto_message *message);
};
# endif /* } */
