using Avalonia.Controls;
using FluentAvalonia.UI.Controls;
using Avalonia;
using macos_app.Models;

namespace macos_app.Views;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();

        new Hierarchy(this);
    }

    public void UpdateHierarchy(HierarchyElement root)
    {
        HierarchyStackPanel.Children.Clear();

        DisplayHierarchyElement(root);
    }

    private void DisplayHierarchyElement(HierarchyElement elem)
    {
        if(elem.name[0] == '.')
            return;

        HierarchyStackPanel.Children.Add(new Button
        {
            Content = "> " + elem.name,
            Margin = new Thickness(elem.depth * 16, 2, 0, 2)
        });

        if(elem.type != Type.Folder)
            return;

        foreach (HierarchyElement child in elem.GetChildren())
        {
            DisplayHierarchyElement(child);
        }
    }
}