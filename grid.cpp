# include	"grid.h"
# include	"tile.h"

grid::grid(int _cols)
{
    layout = new QGridLayout();
    setLayout(layout);
    row = col = 0;
    cols = _cols;
}


grid::~grid()
{
}

void
grid::addTile(QString _title, QString _topic, QString _unit, QSettings *settings)
{
    tile *t = new tile(_title, _topic, _unit, settings);
    layout->addWidget(t, row, col);
    col++;
    if (col >= cols)
    {
        col = 0;
	row++;
    }
}
