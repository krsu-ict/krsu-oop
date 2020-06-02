#ifndef VIEW_H
#define VIEW_H

template<class T>
class View {
public:
    explicit View(const T &model) : _model(model) {}
    virtual ~View() = default;

    virtual void present() = 0;

protected:
    const T &_model;
};

#endif
