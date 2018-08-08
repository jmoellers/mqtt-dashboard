# if !defined GRID_H /* { */
# define GRID_H

# include	<QtWidgets>

class grid : public QFrame
{
public:
    grid(int _cols = 5);
    ~grid();
    void addTile(QString _title, QString _topic, QString _unit, QSettings *settings);
private:
    QGridLayout *layout;
    int cols, row, col;
    QSettings *settings;
};
# endif /* } */
