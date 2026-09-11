using Avalonia.Controls;
using FluentAvalonia.UI.Controls;
using Avalonia;
using macos_app.Models;
using macos_app.ViewModels;
using System;
using System.Collections.Generic;

namespace macos_app.Views;

public partial class MainWindow : Window
{
    private Hierarchy hierarchy;
    private HierarchyElement? currentFolder;

    private List<HierarchyElement> currentFolderImages;
    private int currentImage = 0;

    private bool previewMode = true;

    public MainWindow()
    {
        InitializeComponent();

        hierarchy = new Hierarchy(this);

        currentFolderImages = new List<HierarchyElement>();
        SetCurrentFolder(hierarchy.root, true);

        DataContextChanged += (s, e) =>
        {
            if (DataContext is MainViewModel vm)
            {
                vm.NavigationTriggered += OnNavigation;
                vm.PreviewMode += OnPreview;
            }
        };
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

        var button = new Button
        {
            Content = "> " + elem.name,
            Margin = new Thickness(elem.depth * 16, 2, 0, 2)
        };

        button.Click += (s, e) => OnHierarchyElementClicked(elem.path);

        HierarchyStackPanel.Children.Add(button);

        if(elem.type != Models.Type.Folder)
            return;

        foreach (HierarchyElement child in elem.GetChildren())
        {
            DisplayHierarchyElement(child);
        }
    }

    private void SetCurrentFolder(HierarchyElement? folder, bool updatePreview)
    {
        if(folder == null)
            folder = hierarchy.root;

        if(folder.type != Models.Type.Folder)
            return;

        currentFolder = folder;

        currentFolderImages = currentFolder.GetImageChildren();
        if (updatePreview)
        {
            if(currentFolderImages.Count > 0)
                OnHierarchyElementClicked(currentFolderImages[0].path, false);
            else if(DataContext is MainViewModel vm)
            {
                vm.LoadFile("");
            }
        }
    }

    private void OnHierarchyElementClicked(string path, bool updateFolder=true)
    {
        HierarchyElement element = hierarchy.GetElementByPath(path);

        if (DataContext is MainViewModel vm)
        {
            if (element == null)
            {
                vm.LoadFile("");
                return;
            }

            if(element.type == Models.Type.Folder)
            {
                SetCurrentFolder(element, true);
                return;
            }

            if(updateFolder)
                SetCurrentFolder(element.parent, false); // If a document is selected, we are placed in the parent's folder

            if(element.type == Models.Type.Image) // If an image is selected, we display a preview
            {   
                currentImage = currentFolderImages.IndexOf(element);

                if(previewMode)
                    vm.LoadFile(path);
            }
            else
                vm.LoadFile("");
        }
    }

    private void OnNavigation(int input)
    {
        if(currentFolderImages.Count == 0)
            return;

        currentImage = (currentImage + input) % currentFolderImages.Count;
        if(currentImage < 0)
            currentImage += currentFolderImages.Count;

        OnHierarchyElementClicked(currentFolderImages[currentImage].path, false);
    }

    private void OnPreview(bool preview)
    {
        previewMode = preview;
    }
}